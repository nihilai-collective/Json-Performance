
----
### Google Maps Response Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 843.512 | 0.0734741 | 1254.24ms | 4390 | 640 | 8511.3 | 4963.33 | 0.00340005 | 6.14593 | 27.6474 | 5.56606 | 0.0104474 | 3.09653e-05 | 2.84738e-06 | 1(Win) | true |
| simdjson (ondemand) | 729.198 | 0.0542864 | 1327.43ms | 4390 | 160 | 1554.32 | 5741.42 | 0.00468068 | 7.11583 | 31.441 | 5.72392 | 0.00992454 | 4.41344e-05 | 1.28132e-05 | 2(Loss) | true |
