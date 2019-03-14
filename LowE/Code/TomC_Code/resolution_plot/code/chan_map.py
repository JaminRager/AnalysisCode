#!/usr/bin/env python

class det_map:
    def __init__(self, labels, vals):
        self.data = []
        c = '0'
        p = '0'
        d = '0'
        for label in labels:
            try:
                self.data.append([label, int(vals[labels.index(label)])])
            except ValueError:
                self.data.append([label, vals[labels.index(label)]])
            if label == 'C':
                c = vals[labels.index(label)]
            elif label == 'P':
                p = vals[labels.index(label)]
            elif label == 'D':
                d = vals[labels.index(label)]
        self.data.append(['pos', 'C'+c+'P'+p+'D'+d])
        self.data.append(['str', 'C'+c+'P'+p])
        self.data.append(['row', 'C'+c+'D'+d])
    def dump(self):
        print self.data
    def get_val(self, label):
        l = [row[1] for row in filter(lambda x: x[0] == label, self.data)]
        if len(l) == 1:
            if type(l[0]) == float:
                return l[0]
            else:
                try:
                    return int(l[0])
                except ValueError:
                    return l[0]
        else:
            if len(l) > 0:
                if type(l[0]) == float:
                    return l
            else:
                try:
                    return [int(i) for i in l]
                except ValueError:
                    return l
    def add_data(self, label, val):
        self.data.append([label, val])
        
class chan_map:
    def __init__(self, dataset):
        self.ds = str(dataset)
        self.det = []
        try:
            infile = open('../data/ds'+dataset+'_chan_map.txt')
            labels = []
            for i, line in enumerate(infile):
                if len(labels) == 0:
                    labels = line.split()
                elif line != '':
                    self.det.append(det_map(labels, line.split()))
            infile.close()
        except IOError:
            print 'DS'+dataset, 'channel map not found'
    def get_det(self, label, val):
        l = list(filter(lambda x: x.get_val(label) == val, self.det))
        if len(l) == 1:
            return l[0]
        return l
    def get_val(self, label, val, var, col=False):
        det = self.get_det(label, val)
        try:
            return det.get_val(var)
        except AttributeError:
            l = [m.get_val(var) for m in det]
            if col:
                return filter(lambda i: not(type(i) is list), l)
            else:
                return l
            
class ds_maps:
    def __init__(self):
        self.maps = []
    def get_map(self, ds):
        try:
            return list(filter(lambda m: m.ds == str(ds), self.maps))[0]
        except IndexError:
            m = chan_map(str(ds))
            self.maps.append(m)
            return m
    def add_ds(self, ds):
        self.maps.append(chan_map(str(ds)))
    def get_val(self, ds, label, val, var):
        return self.get_map(ds).get_val(label, val, var)
