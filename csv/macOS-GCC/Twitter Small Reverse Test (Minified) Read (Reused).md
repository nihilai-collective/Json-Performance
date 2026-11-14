
----
### Twitter Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 727.584 | 1.46912 | 400.188ms | 2821 | 160 | 472145 | 3697.6 | 0.303819 | 1(Win) | true |
| simdjson (ondemand) | 329.308 | 0.532327 | 980.343ms | 2821 | 80 | 151303 | 8169.6 | 0.274941 | 2(Loss) | true |
