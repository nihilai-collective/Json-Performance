
----
### Marine IK Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 819.33 | 0.10225 | 1274.5ms | 4604 | 1280 | 38431.6 | 5358.91 | 0.0932592 | 6.24724 | 23.9112 | 5.27129 | 0.00749603 | 5.63369e-05 | 1.37448e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 728.144 | 0.110665 | 1334.3ms | 4604 | 1280 | 56999 | 6030.01 | 0.119013 | 6.98906 | 29.3147 | 6.11816 | 0.0064504 | 0.000104698 | 3.90286e-05 | 2(Loss) | true |
| Glaze | 654.835 | 0.0809501 | 1412.55ms | 4604 | 4890 | 144063 | 6705.08 | 0.322397 | 7.77436 | 32.8602 | 6.67496 | 0.00835883 | 9.16337e-05 | 3.97982e-05 | 3(Loss) | true |
| simdjson (ondemand) | 510.691 | 0.108703 | 1603.24ms | 4604 | 1280 | 111802 | 8597.6 | 0.0527042 | 9.96137 | 39.5821 | 7.00326 | 0.0076759 | 7.38149e-05 | 1.66296e-05 | 4(Loss) | true |
