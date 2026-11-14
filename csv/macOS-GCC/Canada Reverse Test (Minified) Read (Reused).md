
----
### Canada Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 506.653 | 0.714246 | 7062.29ms | 2090234 | 30 | 2.36912e+10 | 3.93446e+06 | 1.1892 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 493.414 | 1.51203 | 7569.84ms | 2090234 | 30 | 1.11946e+11 | 4.04002e+06 | 3.43123 | 1(Tie) | true |
