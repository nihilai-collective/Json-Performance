
----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2839.02 | 0.0612875 | 1178.44ms | 11812 | 80 | 473.091 | 3967.85 | 0.0157491 | 1.80017 | 9.20166 | 1.40019 | 0.00169848 | 3.06891e-05 | 2.11649e-06 | 1(Win) | true |
| Glaze | 2209.02 | 0.0750669 | 1287.92ms | 11812 | 1280 | 18756.7 | 5099.46 | 0.0116573 | 2.32553 | 12.0412 | 2.3786 | 0.000666496 | 1.95114e-05 | 4.16684e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 1963.54 | 0.0777474 | 1374.17ms | 11812 | 80 | 1591.58 | 5736.99 | 0.0703272 | 2.64315 | 12.65 | 1.9321 | 0.00639815 | 1.37572e-05 | 1.05825e-06 | 3(Loss) | true |
| simdjson (reflection) | 1606.83 | 0.0583268 | 1500.2ms | 11812 | 160 | 2675.24 | 7010.57 | 0.0663735 | 3.16644 | 12.982 | 2.02921 | 0.00335094 | 2.43397e-05 | 1.58737e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1170.67 | 0.063382 | 1753.45ms | 11812 | 80 | 2975.77 | 9622.52 | 0.0519884 | 4.33893 | 17.0127 | 3.02946 | 0.00775377 | 4.86793e-05 | 2.22232e-05 | 5(Loss) | true |
