
----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2466.02 | 0.233115 | 1200.35ms | 11812 | 160 | 18143.1 | 4568 | 0.0301098 | 2.07206 | 9.98112 | 1.74729 | 0.00365677 | 1.11116e-05 | 5.29123e-07 | 1(Win) | true |
| Jsonifier (two-stage) | 1859.7 | 0.126605 | 1355.95ms | 11812 | 2560 | 150558 | 6057.33 | 0.0581633 | 2.73563 | 13.4227 | 2.2914 | 0.0046251 | 5.48965e-05 | 2.6853e-05 | 2(Loss) | true |
| Glaze | 1804.26 | 0.0800003 | 1371.3ms | 11812 | 4890 | 121995 | 6243.45 | 0.0491451 | 2.81772 | 13.6889 | 2.65442 | 0.00105032 | 6.00928e-05 | 2.80468e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1062.66 | 0.0856097 | 1810.88ms | 11812 | 4890 | 402733 | 10600.6 | 0.0862305 | 4.77391 | 20.5059 | 3.40817 | 0.00800742 | 7.35795e-05 | 3.53355e-05 | 4(Loss) | true |
