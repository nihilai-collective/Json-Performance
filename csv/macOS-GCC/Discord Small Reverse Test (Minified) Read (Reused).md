
----
### Discord Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 680.916 | 0.21857 | 729.04ms | 4857 | 2560 | 565942 | 6802.6 | 0.0411777 | 1(Win) | true |
| simdjson (ondemand) | 167.214 | 0.144634 | 2827.51ms | 4857 | 4890 | 7.84954e+06 | 27701.1 | 0.628546 | 2(Loss) | true |
