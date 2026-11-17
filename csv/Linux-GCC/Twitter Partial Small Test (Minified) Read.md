
----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5499.13 | 0.133818 | 778.169ms | 2889 | 320 | 143.843 | 501.019 | 0.100942 | 0.994484 | 3.89166 | 0.51298 | 0.000352631 | 5.08394e-05 | 8.65351e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 5473.08 | 0.0444554 | 779.74ms | 2889 | 2560 | 128.209 | 503.403 | 0.121292 | 0.998861 | 3.89166 | 0.51298 | 0.000346276 | 2.90704e-05 | 5.67887e-06 | 2(Loss) | true |
| simdjson (ondemand) | 5441.91 | 0.0944659 | 779.638ms | 2889 | 4890 | 1118.54 | 506.287 | 0.0672817 | 1.00351 | 3.89997 | 0.416753 | 0.000720171 | 1.91828e-05 | 2.83142e-06 | 3(Loss) | true |
| simdjson (reflection) | 5214.58 | 0.117122 | 777.779ms | 2889 | 4890 | 1872.58 | 528.358 | 0.0464701 | 1.04157 | 3.87643 | 0.422639 | 0.000858981 | 3.91443e-05 | 1.21043e-05 | 4(Loss) | true |
| Glaze | 3082.08 | 0.0363891 | 817.662ms | 2889 | 4890 | 517.438 | 893.929 | 0.22526 | 1.7148 | 7.24922 | 1.24264 | 0.00034699 | 2.57659e-05 | 5.73362e-06 | 5(Loss) | true |
