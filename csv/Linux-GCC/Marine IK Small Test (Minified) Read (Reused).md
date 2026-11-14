
----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 622.411 | 0.0860602 | 1520.93ms | 4604 | 1280 | 47177.1 | 7054.37 | 0.0715383 | 8.33668 | 34.1236 | 6.42708 | 0.00858374 | 7.00817e-05 | 2.49443e-05 | 1(Win) | true |
| Jsonifier (generic) | 605.725 | 0.0308968 | 1549.91ms | 4604 | 4890 | 24527.6 | 7248.7 | 0.225082 | 8.56053 | 32.6204 | 6.73098 | 0.0123566 | 5.92976e-05 | 1.73673e-05 | 2(Loss) | true |
