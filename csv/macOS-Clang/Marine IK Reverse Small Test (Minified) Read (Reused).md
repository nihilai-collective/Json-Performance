
----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 824.381 | 0.104233 | 675.523ms | 4604 | 40 | 1232.79 | 5326.07 | 0.0464911 | 1(Win) | true |
| Jsonifier (two-stage) | 689.36 | 0.0804585 | 793.079ms | 4604 | 80 | 2100.93 | 6369.26 | 0.0241452 | 2(Loss) | true |
| Glaze | 446.7 | 0.0768591 | 1122.29ms | 4604 | 30 | 1712.19 | 9829.23 | 0.0135631 | 3(Loss) | true |
| simdjson (ondemand) | 361.275 | 0.0366333 | 1374.07ms | 4604 | 160 | 3171.51 | 12153.4 | 0.0656793 | 4(Loss) | true |
