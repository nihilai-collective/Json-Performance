
----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2269.38 | 0.0331903 | 3546.2ms | 53331 | 4890 | 270567 | 22411.5 | 0.0245152 | 2.2206 | 7.66137 | 1.22524 | 0.0075112 | 2.20485e-05 | 1.11546e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2043.29 | 0.0534746 | 3808.5ms | 53331 | 2560 | 453560 | 24891.5 | 0.051099 | 2.46816 | 8.52551 | 1.31658 | 0.0073471 | 4.8071e-05 | 1.95858e-05 | 2(Loss) | true |
| Glaze | 1948.83 | 0.0505018 | 3942.48ms | 53331 | 4890 | 849441 | 26097.9 | 0.0477335 | 2.59435 | 9.40859 | 1.77395 | 0.0157468 | 3.29999e-05 | 1.73972e-05 | 3(Loss) | true |
| simdjson (reflection) | 1898.19 | 0.106618 | 4006.39ms | 53331 | 640 | 522299 | 26794.2 | 0.111624 | 2.67362 | 8.97365 | 1.46675 | 0.00906713 | 8.09215e-05 | 2.59582e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1627.27 | 0.0670803 | 4409.94ms | 53331 | 640 | 281325 | 31255 | 0.0106772 | 3.10053 | 9.22513 | 1.63481 | 0.00983627 | 4.86349e-05 | 2.26182e-05 | 5(Loss) | true |
