
----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 937.906 | 0.113632 | 1305.64ms | 4604 | 4890 | 138376 | 4681.4 | 0.374414 | 5.44936 | 20.9603 | 4.56494 | 0.00551015 | 0.000151686 | 8.15509e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 795.045 | 0.111512 | 1392.43ms | 4604 | 4890 | 185455 | 5522.6 | 0.165595 | 6.41116 | 25.8008 | 5.24696 | 0.00576821 | 7.37333e-05 | 2.65618e-05 | 2(Loss) | true |
| Glaze | 718.798 | 0.0607924 | 1441.46ms | 4604 | 4890 | 67431.9 | 6108.42 | 0.0319959 | 7.07998 | 29.4028 | 5.87337 | 0.006815 | 7.57766e-05 | 2.7761e-05 | 3(Loss) | true |
| simdjson (ondemand) | 566.308 | 0.0702098 | 1617.71ms | 4604 | 4890 | 144900 | 7753.22 | 0.120833 | 8.99907 | 37.068 | 6.46981 | 0.00669166 | 0.000335309 | 0.000198858 | 4(Loss) | true |
