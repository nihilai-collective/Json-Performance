
----
### Discord Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1884.4 | 0.0441123 | 995.326ms | 4857 | 4890 | 5749.36 | 2458.08 | 0.115175 | 2.76833 | 11.5722 | 2.06713 | 0.00194428 | 4.23566e-05 | 8.42079e-06 | 1(Win) | true |
| simdjson (ondemand) | 1639.69 | 0.0710101 | 1038.98ms | 4857 | 4890 | 19677 | 2824.92 | 0.102955 | 3.16061 | 13.0568 | 2.08153 | 0.000610844 | 6.21455e-05 | 2.13888e-05 | 2(Loss) | true |
