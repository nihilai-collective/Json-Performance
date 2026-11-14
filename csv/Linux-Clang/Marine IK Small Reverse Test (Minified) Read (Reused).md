
----
### Marine IK Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 349.729 | 0.0173331 | 2075.52ms | 4604 | 4890 | 23156.4 | 12554.6 | 0.0534213 | 14.7757 | 64.6384 | 13.6095 | 0.0180891 | 0.000135252 | 7.29338e-05 | 1(Win) | true |
| simdjson (ondemand) | 235.184 | 0.0303466 | 2678.86ms | 4604 | 1280 | 41084.9 | 18669.2 | 0.0253779 | 21.9424 | 104.945 | 20.9355 | 0.0235108 | 0.000150345 | 6.77061e-05 | 2(Loss) | true |
