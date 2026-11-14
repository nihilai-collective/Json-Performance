
----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13723.7 | 0.242782 | 745.322ms | 2632 | 40 | 7.88718 | 182.9 | 0.218221 | 0.451966 | 1.52546 | 0.240502 | 0.000379939 | 0 | 0 | 1(Win) | true |
| simdjson (reflection) | 8122.62 | 0.0600042 | 762.525ms | 2632 | 2560 | 88.0202 | 309.022 | 0.0360129 | 0.705745 | 2.52356 | 0.406155 | 0.000379939 | 3.56193e-05 | 1.52866e-05 | 2(Loss) | true |
| Glaze | 5243.68 | 0.101088 | 772.38ms | 2632 | 2560 | 599.431 | 478.685 | 0.0980731 | 1.04563 | 3.59005 | 0.569529 | 0.000380681 | 1.91454e-05 | 5.49131e-06 | 3(Loss) | true |
