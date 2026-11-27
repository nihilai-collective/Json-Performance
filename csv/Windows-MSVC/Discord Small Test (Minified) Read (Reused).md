
----
### Discord Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1272.98 | 0.0686277 | 413.602ms | 4857 | 4890 | 30492.9 | 3638.69 | 0.0809915 | 2.37591 | 1(Win) | true |
| simdjson (ondemand) | 1024.46 | 0.0954864 | 499.594ms | 4857 | 2560 | 47716.7 | 4521.41 | 0.08632 | 2.95315 | 2(Loss) | true |
