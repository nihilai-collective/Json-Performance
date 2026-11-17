
----
### Marine IK Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 349.514 | 0.0301401 | 2086.02ms | 4604 | 1280 | 18350.2 | 12562.4 | 0.0622845 | 14.7809 | 64.4279 | 13.9067 | 0.0188208 | 5.88822e-05 | 1.01814e-05 | 1(Win) | true |
| simdjson (ondemand) | 256.173 | 0.0316366 | 2534.92ms | 4604 | 2560 | 75270.5 | 17139.7 | 0.0952258 | 20.144 | 106.184 | 21.1985 | 0.0210353 | 0.000179786 | 7.89904e-05 | 2(Loss) | true |
