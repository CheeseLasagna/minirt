/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listadd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlavelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 09:43:52 by tlavelle          #+#    #+#             */
/*   Updated: 2020/10/27 09:43:54 by tlavelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	lst_addback_plane(t_plane **root, t_plane *nw)
{
	t_plane *temp;

	temp = *root;
	if (*root == NULL)
	{
		nw->next = NULL;
		*root = nw;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	nw->next = NULL;
	temp->next = nw;
}

void	lst_addback_sphere(t_sphere **root, t_sphere *nw)
{
	t_sphere *temp;

	temp = *root;
	if (*root == NULL)
	{
		nw->next = NULL;
		*root = nw;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	nw->next = NULL;
	temp->next = nw;
}

void	lst_addback_square(t_square **root, t_square *nw)
{
	t_square *temp;

	temp = *root;
	if (*root == NULL)
	{
		nw->next = NULL;
		*root = nw;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	nw->next = NULL;
	temp->next = nw;
}

void	lst_addback_cylinder(t_cylinder **root, t_cylinder *nw)
{
	t_cylinder *temp;

	temp = *root;
	if (*root == NULL)
	{
		nw->next = NULL;
		*root = nw;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	nw->next = NULL;
	temp->next = nw;
}

void	lst_addback_triangle(t_triangle **root, t_triangle *nw)
{
	t_triangle *temp;

	temp = *root;
	if (*root == NULL)
	{
		nw->next = NULL;
		*root = nw;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	nw->next = NULL;
	temp->next = nw;
}
