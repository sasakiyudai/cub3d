/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syudai <syudai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 23:51:21 by syudai            #+#    #+#             */
/*   Updated: 2020/12/19 15:13:45 by syudai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_H
# define KEY_H
# ifdef __linux__
#  define K_A 97
#  define K_D 100
#  define K_S 115
#  define K_W 119
#  define K_AR_L 65361
#  define K_AR_R 65363
#  define K_ESC 65307
# else
#  define K_A 0
#  define K_D 2
#  define K_S 1
#  define K_W 13
#  define K_AR_L 123
#  define K_AR_R 124
#  define K_ESC 53
# endif
#endif
