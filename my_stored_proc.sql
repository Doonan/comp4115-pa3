delimiter //
create procedure fullname
(in arg varchar(50))
begin
select first_name, last_name from employees
where first_name = arg or last_name = arg;
end //

create procedure avgsalary
(in arg char(4))
begin
select sum(salary)/count(*) from salaries where emp_no in 
(select emp_no from dept_emp where dept_no = arg);
end //

create procedure sexlist
(in arg enum('M','F'))
begin
select count(*) from employees where gender=arg;
end //
delimiter ;