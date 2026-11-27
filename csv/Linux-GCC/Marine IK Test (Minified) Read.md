
----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 843.06 | 0.0671774 | 6476.29ms | 1834197 | 160 | 3.10843e+08 | 2.07485e+06 | 0.0815004 | 5.98236 | 25.2965 | 5.64135 | 0.0375266 | 0.0845141 | 0.000316126 | 1(Win) | true |
| Jsonifier (two-stage) | 717.184 | 0.156582 | 7575.01ms | 1834197 | 30 | 4.37558e+08 | 2.43902e+06 | 0.0283541 | 6.98586 | 29.5667 | 6.15309 | 0.046574 | 0.148468 | 0.000224313 | 2(Loss) | true |
| simdjson (reflection) | 668.644 | 0.0691269 | 8128.67ms | 1834197 | 80 | 2.6163e+08 | 2.61608e+06 | 0.11404 | 7.5395 | 32.2928 | 5.99748 | 0.0319811 | 0.136688 | 0.000303171 | 3(Loss) | true |
| Glaze | 647.262 | 0.166133 | 8427.65ms | 1834197 | 40 | 8.06312e+08 | 2.7025e+06 | 0.043386 | 7.84897 | 32.3365 | 6.31508 | 0.0347183 | 0.082787 | 0.00227151 | 4(Loss) | true |
| simdjson (ondemand) | 561.892 | 0.233165 | 9700.79ms | 1834197 | 30 | 1.58065e+09 | 3.1131e+06 | 0.471729 | 8.95474 | 36.9666 | 7.14919 | 0.0373869 | 0.149423 | 0.00013659 | 5(Loss) | true |
