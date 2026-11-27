
----
### Google Maps Response Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2577.98 | 0.0556073 | 1165.39ms | 11812 | 2560 | 15114.5 | 4369.63 | 0.0500454 | 1.98484 | 9.89035 | 1.59948 | 0.00261757 | 1.92468e-05 | 4.72904e-06 | 1(Win) | true |
| Glaze | 1920.03 | 0.0619378 | 1320.53ms | 11812 | 1280 | 16902.6 | 5866.99 | 0.225728 | 2.65314 | 13.1236 | 2.62724 | 0.00203296 | 5.16556e-05 | 2.4009e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1677.53 | 0.0865354 | 1409.49ms | 11812 | 640 | 21610.9 | 6715.09 | 0.0445091 | 3.06481 | 14.8052 | 2.29445 | 0.0077703 | 6.13783e-05 | 2.83081e-05 | 3(Loss) | true |
| simdjson (reflection) | 1573.29 | 0.0294825 | 1453.58ms | 11812 | 4890 | 21790.5 | 7160.03 | 0.0543102 | 3.23606 | 12.8495 | 2.04834 | 0.00442954 | 4.40092e-05 | 1.87325e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1225.97 | 0.0867425 | 1664.93ms | 11812 | 320 | 20328.3 | 9188.49 | 0.047931 | 4.21176 | 17.2639 | 3.08812 | 0.00667356 | 1.05825e-05 | 0 | 5(Loss) | true |
