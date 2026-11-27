
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2415.79 | 0.105299 | 834.088ms | 2632 | 160 | 191.521 | 1039.03 | 0.0397164 | 2.21604 | 9.07029 | 1.57105 | 0.000764628 | 4.74924e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1903.48 | 0.0571929 | 857.612ms | 2632 | 4890 | 2781.42 | 1318.67 | 0.149103 | 2.78069 | 10.3986 | 1.71847 | 0.00225229 | 4.55305e-05 | 1.07222e-05 | 2(Loss) | true |
