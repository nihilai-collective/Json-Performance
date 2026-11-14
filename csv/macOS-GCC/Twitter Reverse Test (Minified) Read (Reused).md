
----
### Twitter Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 682.981 | 0.0740468 | 5054.84ms | 264040 | 320 | 2.38498e+07 | 368690 | 0.166922 | 1(Win) | true |
| simdjson (ondemand) | 293.268 | 0.0868639 | 5657.4ms | 264040 | 160 | 8.90036e+07 | 858627 | 0.115293 | 2(Loss) | true |
