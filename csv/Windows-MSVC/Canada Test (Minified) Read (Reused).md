
----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 458.753 | 0.657398 | 7657.47ms | 2090234 | 30 | 2.44799e+10 | 4.34526e+06 | 0.760599 | 6.6244 | 1(Win) | true |
| simdjson (ondemand) | 420.406 | 0.836012 | 7964.29ms | 2090234 | 40 | 6.28547e+10 | 4.74162e+06 | 0.015727 | 7.22919 | 2(Loss) | true |
