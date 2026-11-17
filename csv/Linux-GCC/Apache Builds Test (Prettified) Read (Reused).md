
----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2625.58 | 0.0277854 | 6535.97ms | 124597 | 2560 | 404799 | 45256.7 | 0.0176704 | 1.91424 | 9.32803 | 1.41992 | 0.00507765 | 1.05371e-05 | 7.53053e-06 | 1(Win) | true |
| simdjson (ondemand) | 2435.87 | 0.127293 | 6900.62ms | 124597 | 80 | 308464 | 48781.4 | 0.0586713 | 2.06772 | 8.45646 | 1.55537 | 0.00567841 | 5.91908e-06 | 2.90938e-06 | 2(Loss) | true |
| Jsonifier | 2383.78 | 0.0455524 | 6975.22ms | 124597 | 640 | 329978 | 49847.2 | 0.087541 | 2.10955 | 9.41571 | 1.67292 | 0.00800457 | 6.44578e-06 | 3.34829e-06 | 3(Loss) | true |
| simdjson (reflection) | 2333.22 | 0.0313867 | 7125.63ms | 124597 | 2560 | 654085 | 50927.4 | 0.0203924 | 2.16548 | 8.77219 | 1.46003 | 0.00335046 | 1.74688e-05 | 1.3365e-05 | 4(Loss) | true |
| Glaze | 2134.72 | 0.0361924 | 7630.21ms | 124597 | 2560 | 1.03898e+06 | 55662.9 | 0.172055 | 2.36119 | 10.929 | 2.09467 | 0.0103069 | 1.02988e-05 | 6.00373e-06 | 5(Loss) | true |
