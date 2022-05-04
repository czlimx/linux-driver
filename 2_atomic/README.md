# atomic_t
```c
include\linux\types.h

typedef struct {
	int counter;
} atomic_t;
```
# api:
```c
\arch\arm\include\asm\atomic.h

#define atomic_read(v)	READ_ONCE((v)->counter)
#define atomic_set(v,i)	WRITE_ONCE(((v)->counter), (i))

#define atomic_xchg(v, new) (xchg(&((v)->counter), new))

#define atomic_inc(v)		atomic_add(1, v)
#define atomic_dec(v)		atomic_sub(1, v)

#define atomic_inc_and_test(v)	(atomic_add_return(1, v) == 0)
#define atomic_dec_and_test(v)	(atomic_sub_return(1, v) == 0)
#define atomic_inc_return_relaxed(v)    (atomic_add_return_relaxed(1, v))
#define atomic_dec_return_relaxed(v)    (atomic_sub_return_relaxed(1, v))
#define atomic_sub_and_test(i, v) (atomic_sub_return(i, v) == 0)

#define atomic_add_negative(i,v) (atomic_add_return(i, v) < 0)
```
# atomic_add
```c
arch\arm\include\asm\atomic.h

#define ATOMIC_OPS(op, c_op, asm_op)					\
	ATOMIC_OP(op, c_op, asm_op)					\
	ATOMIC_OP_RETURN(op, c_op, asm_op)				\
	ATOMIC_FETCH_OP(op, c_op, asm_op)
	
#define ATOMIC_OP(op, c_op, asm_op)					\
static inline void atomic_##op(int i, atomic_t *v)			\
{									\
	unsigned long flags;						\
									\
	raw_local_irq_save(flags);					\
	v->counter c_op i;						\
	raw_local_irq_restore(flags);					\
}
	
#define ATOMIC_OP_RETURN(op, c_op, asm_op)				\
static inline int atomic_##op##_return(int i, atomic_t *v)		\
{									\
	unsigned long flags;						\
	int val;							\
									\
	raw_local_irq_save(flags);					\
	v->counter c_op i;						\
	val = v->counter;						\
	raw_local_irq_restore(flags);					\
									\
	return val;							\
}
	
#define ATOMIC_FETCH_OP(op, c_op, asm_op)				\
static inline int atomic_fetch_##op(int i, atomic_t *v)			\
{									\
	unsigned long flags;						\
	int val;							\
									\
	raw_local_irq_save(flags);					\
	val = v->counter;						\
	v->counter c_op i;						\
	raw_local_irq_restore(flags);					\
									\
	return val;							\
}
```

## atomic_add解析
```c
ATOMIC_OPS(add, +=, add)
#define atomic_dec(v)		atomic_sub(1, v)

ATOMIC_OP(add, +=, add)					\
ATOMIC_OP_RETURN(add, +=, add)				\
ATOMIC_FETCH_OP(add, +=, add)

static inline void atomic_add(int i, atomic_t *v)
{
	unsigned long flags;
	
	raw_local_irq_save(flags);
	v->counter += i;
	raw_local_irq_restore(flags);
}

static inline int atomic_add_return(int i, atomic_t *v)
{
	unsigned long flags;
	int val;

	raw_local_irq_save(flags);
	v->counter += i;
	val = v->counter;
	raw_local_irq_restore(flags);
	
	return val;
}

static inline int atomic_fetch_add(int i, atomic_t *v)
{
	unsigned long flags;
	int val;

	raw_local_irq_save(flags);
	val = v->counter;
	v->counter += i;
	raw_local_irq_restore(flags);
	
	return val;	
}	
```
`ATOMIC_OPS(add, +=, add)`宏定义自动生成了：
- atomic_add
- atomic_add_return
- atomic_fetch_add

## raw_local_irq_save / raw_local_irq_restore解析
```
include\linux\typecheck.h

#define typecheck(type,x) \
({	type __dummy; \
	typeof(x) __dummy2; \
	(void)(&__dummy == &__dummy2); \
	1; \
})

include\linux\irqflags.h

#define raw_local_irq_save(flags)			\
	do {						\
		typecheck(unsigned long, flags);	\
		flags = arch_local_irq_save();		\
	} while (0)
#define raw_local_irq_restore(flags)			\
	do {						\
		typecheck(unsigned long, flags);	\
		arch_local_irq_restore(flags);		\
	} while (0)
	
#define arch_local_irq_save arch_local_irq_save
static inline unsigned long arch_local_irq_save(void)
{
	unsigned long flags;

	asm volatile(
		"	mrs	%0, " IRQMASK_REG_NAME_R "	@ arch_local_irq_save\n"
		"	cpsid	i"
		: "=r" (flags) : : "memory", "cc");
	return flags;
}

#define arch_local_irq_restore arch_local_irq_restore
static inline void arch_local_irq_restore(unsigned long flags)
{
	asm volatile(
		"	msr	" IRQMASK_REG_NAME_W ", %0	@ local_irq_restore"
		:
		: "r" (flags)
		: "memory", "cc");
}
```
`typeof`是一个运算符，有2种使用方式：`typeof(表达式)`和`typeof 变量名`，第一种是对表达式做运算，第二种是对变量做运算。`typeof`返回值：
| 返回值      | 注解       |
| ------------- |:-------------:|
| undefined    | 未定义的变量或值 						|
| boolean     | 布尔类型的变量或值     		 |
| string 			 | 字符串类型的变量或值      	 |
| number 			 | 数字类型的变量或值      		|
| object 			 | 对象类型的变量或值，或者null |
| function 			| 函数类型的变量或值 					|

`&__dummy == &__dummy2`当类型不一致时编译器会发出`warning`。

`arch_local_irq_save`和`arch_local_irq_restore`就是对`cpsr`寄存器的操作，`cpsr`寄存器会使能/禁止本地CPU的`FIQ IRQ`。

# 示例
```c
struct xxx_dev_struct{
	...
	atomic_t atomic;
};
static struct xxx_dev_struct xxx_dev;

ssize_t xxx_read(struct file *filp, char __user *buf, size_t size, loff_t *ofs)
{
	struct xxx_dev_struct *dev = filp->private_data;
	atomic_sub(1, &dev->atomic);
}

ssize_t xxx_write(struct file *filp, const char __user *buf, size_t size, loff_t *ofs)
{
	struct xxx_dev_struct *dev = filp->private_data;
	atomic_add(1, &dev->atomic);
}

int xxx_open(struct inode *inode, struct file *filp)
{
	filp->private_data = &xxx_dev;
}

static int __init xxx_init(void)
{
	atomic_set(&xxx_dev.atomic, 0);
}
```
