
----
### Marine IK Reverse Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (reflection) | 1506.75 | 0.069922 | 1031.04ms | 4918 | 1280 | 6063.63 | 3112.77 | 0.304914 | 3.42602 | 11.3817 | 1.34994 | 0.000647494 | 4.40029e-05 | 1.87449e-05 | 1(Win) | true |
| Jsonifier | 1451.33 | 0.0752843 | 1026.99ms | 4604 | 4890 | 25366.3 | 3025.31 | 0.101488 | 3.5877 | 9.57515 | 0.570157 | 0.000605591 | 4.80599e-05 | 2.25198e-05 | 2(Loss) | true |
| Glaze | 1194.46 | 0.0513428 | 1092.73ms | 4604 | 4890 | 17417.9 | 3675.9 | 0.0686551 | 4.33119 | 12.8554 | 1.10687 | 0.000551623 | 4.62388e-05 | 1.52353e-05 | 3(Loss) | true |
