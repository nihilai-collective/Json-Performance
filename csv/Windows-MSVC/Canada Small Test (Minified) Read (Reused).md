
----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 681.406 | 0.184921 | 846.898ms | 4630 | 40 | 5743.59 | 6480 | 0.0514139 | 3.61654 | 1(Win) | true |
| Jsonifier (two-stage) | 589.324 | 0.138402 | 922.633ms | 4630 | 40 | 4301.28 | 7492.5 | 0.167112 | 4.18091 | 2(Loss) | true |
| Glaze | 176.452 | 0.299845 | 2703.59ms | 4630 | 640 | 3.60317e+06 | 25023.9 | 0.185104 | 14.0149 | 3(Loss) | true |
| simdjson (ondemand) | 172.903 | 0.853395 | 2702.79ms | 4630 | 40 | 1.89984e+06 | 25537.5 | 0.0947217 | 14.2987 | 4(Loss) | true |
