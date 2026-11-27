
----
### Discord Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1746.21 | 0.401869 | 314.147ms | 4857 | 2560 | 290905 | 2652.6 | 0.143461 | 1(Win) | true |
| simdjson (ondemand) | 1079.42 | 0.611903 | 491.36ms | 4857 | 320 | 220634 | 4291.2 | 0.411831 | 2(Loss) | true |
