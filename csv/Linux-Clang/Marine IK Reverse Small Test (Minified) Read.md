
----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 808.092 | 0.0829041 | 1289.62ms | 4604 | 4890 | 99222.5 | 5433.44 | 0.188108 | 6.32467 | 24.6127 | 5.38814 | 0.00596876 | 0.000145601 | 7.41331e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 703.729 | 0.227042 | 1364.7ms | 4604 | 640 | 128425 | 6239.22 | 0.0618935 | 7.22855 | 28.3278 | 5.79453 | 0.00715377 | 5.12462e-05 | 8.14509e-06 | 2(Loss) | true |
| Glaze | 627.787 | 0.108215 | 1440.13ms | 4604 | 1280 | 73320.7 | 6993.96 | 0.0677718 | 8.09646 | 33.8239 | 6.88532 | 0.00483157 | 8.22994e-05 | 3.12228e-05 | 3(Loss) | true |
| simdjson (ondemand) | 501.747 | 0.0872611 | 1619.81ms | 4604 | 2560 | 149273 | 8750.85 | 0.000785632 | 10.1162 | 40.6659 | 7.28693 | 0.00676569 | 0.00016952 | 7.34755e-05 | 4(Loss) | true |
