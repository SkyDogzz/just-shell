/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandry <yandry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:25:07 by yandry            #+#    #+#             */
/*   Updated: 2025/02/01 15:12:14 by yandry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

# pragma region ft_memory

void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

# pragma endregion

# pragma region ft_string

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *nptr);
char	*ft_strdup(const char *s);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strtrim(const char *s1, const char *set);
char	**ft_split(const char *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strappend(char **s1, const char *s2);

# pragma endregion

# pragma region ft_file

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_get_next_line(int fd);

# pragma endregion

# pragma region ft_list

/**
 * @brief Allocates a new t_list* with the given content
 * 
 * @param content The content to put in the new t_list*
 * @return t_list* The new t_list* with the given content,
 * NULL if the allocation failed
 */
t_list	*ft_lstnew(void *content);

/**
 * @brief Adds a new t_list* to the front of the list
 * 
 * @param lst The list to add to
 * @param nw The new t_list* to add
 */
void	ft_lstadd_front(t_list **lst, t_list *nw);

/**
 * @brief Adds a new t_list* to the back of the list
 * 
 * @param lst The list to add to
 * @param nw The new t_list* to add
 */
void	ft_lstadd_back(t_list **lst, t_list *nw);

/**
 * @brief Counts the number of elements in a t_list*
 * 
 * @param lst The list to count
 * @return int The number of elements in the list
 */
int		ft_lstsize(t_list *lst);

/**
 * @brief Finds the length of a t_list* until a certain character
 * 
 * @param list The list to search
 * @param c The character to search for
 * @return int The length of the list until the character is found
 */
int		ft_lstlentochr(t_list *list, int c);

/**
 * @brief Finds the index of a character in a t_list*
 * 
 * @param list The list to search
 * @param c The character to search for
 * @return int The index of the character in the list,
 * -1 if the character is not found
 */
int		ft_lstfoundchr(t_list *list, int c);

/**
 * @brief Retrieves the last element of a t_list*
 * 
 * @param lst The list to retrieve the last element from
 * @return t_list* The last element of the list
 */
t_list	*ft_lstlast(t_list *lst);

/**
 * @brief Deletes an element from a t_list* using a custom deletion function
 * that frees the content of the element, then frees the element itself
 * 
 * @param lst The node to delete
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *));

/**
 * @brief Deletes all elements of a t_list* using a custom deletion function
 * that frees the content of the elements, then frees the elements themselves
 * 
 * @param lst The list to delete
 */
void	ft_lstclear(t_list **lst, void (*del)(void *));

/**
 * @brief Copies the content of a t_list into a "line" of memory
 * 
 * @param list The list to copy from
 * @param line The line to copy to
 */
void	ft_lstcpyline(t_list *list, void *line);

/**
 * @brief Iterates over a t_list* and applies a function to 
 * the content of each element
 * 
 * @param lst The list to iterate over
 * @param f The function to apply to each element
 */
void	ft_lstiter(t_list *lst, void (*f)(void *));

/**
 * @brief Iterates over a t_list* and applies a function to
 * the content of each element, then creates a new t_list*
 * with the results
 * 
 * @param lst The list to iterate over
 * @param f The function to apply to each element
 * @param del The function to delete the content of the new list
 * @return t_list* The new list with the results of the function 
 * applied to each element,
 * NULL if the allocation failed
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/**
 * @brief
 * Copies the content of a t_list* into an array of whatever type the content is
 * For more complex types, use ft_lsttoarray_c
 * @param lst The list to copy from
 * @param elem_size The size of the elements' type in the list
 * @return void** A pointer to the array of elements,
 * or NULL if the heap failed horribly... Yay :D!!!!
 */
void	**ft_lsttoarray_s(t_list *lst, ssize_t elem_size);

/**
 * @brief
 * Copies the content of a t_list* into an array of whatever type the content is
 * This function is more complex than ft_lsttoarray_s,
 * but it allows for custom copying functions
 * @param lst The list to copy from
 * @param copy_func The function to use to copy the elements
 * @return void** A pointer to the array of elements,
 * or NULL if the heap failed horribly... Yay :D!!!!
 */
void	**ft_lsttoarray_c(t_list *lst, void *(*copy_func)(const void *));
# pragma endregion

# pragma region ft_printf

int		ft_printf(const char *format, ...);
int		ft_putstr(const char *str);
int		ft_putchar(char c);
int		ft_putnbr(int n);
int		ft_putptr(void *ptr);

# pragma endregion

#endif
