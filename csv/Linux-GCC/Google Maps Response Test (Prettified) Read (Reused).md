
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3542.22 | 0.0462935 | 1475.32ms | 25388 | 2560 | 25632.2 | 6835.22 | 0.0351246 | 1.43054 | 6.77734 | 0.960533 | 0.00302344 | 1.58786e-05 | 7.00072e-06 | 1(Win) | true |
| Jsonifier | 3498.2 | 0.0353592 | 1482.7ms | 25388 | 4890 | 29287.4 | 6921.24 | 0.00431019 | 1.45125 | 6.80696 | 1.29301 | 0.00395209 | 1.31618e-05 | 2.51314e-06 | 2(Loss) | true |
| simdjson (reflection) | 3165.06 | 0.0340488 | 1558.73ms | 25388 | 4890 | 33174.7 | 7649.75 | 0.0308052 | 1.59491 | 6.74409 | 0.973531 | 0.00120446 | 2.06851e-05 | 9.45651e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2358.34 | 0.0304804 | 1821.78ms | 25388 | 2560 | 25068.4 | 10266.5 | 0.0100648 | 2.14473 | 8.61999 | 1.43891 | 0.00354177 | 1.0878e-05 | 2.95415e-06 | 4(Loss) | true |
| Glaze | 1973.89 | 0.0291076 | 2008.9ms | 25388 | 2560 | 32633.5 | 12266.1 | 0.0768013 | 2.56476 | 8.93158 | 1.6984 | 0.00544082 | 1.32783e-05 | 2.29254e-06 | 5(Loss) | true |
