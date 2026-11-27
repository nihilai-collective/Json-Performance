
----
### Discord Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 756.59 | 0.0647023 | 1346.76ms | 4857 | 1280 | 20084.6 | 6122.2 | 0.10801 | 6.88766 | 29.6146 | 5.97241 | 0.0056941 | 7.86558e-05 | 3.86041e-05 | 1(Win) | true |
| simdjson (ondemand) | 219.432 | 0.0284344 | 2833.86ms | 4857 | 4890 | 176170 | 21109 | 0.704103 | 23.1706 | 115.717 | 22.2961 | 0.0425222 | 0.000216667 | 0.000134775 | 2(Loss) | true |
