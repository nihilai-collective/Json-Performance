
----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 531.686 | 0.52991 | 6668.02ms | 2090234 | 80 | 3.15772e+10 | 3.74921e+06 | 0.743346 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 521.896 | 0.875458 | 6648.41ms | 2090234 | 40 | 4.47252e+10 | 3.81954e+06 | 1.41616 | 1(Tie) | true |
