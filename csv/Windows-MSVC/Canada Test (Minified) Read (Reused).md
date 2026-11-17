
----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 206.637 | 0.964908 | 7133.1ms | 2090234 | 40 | 3.46581e+11 | 9.64687e+06 | 1.60053 | 11.9815 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 202.095 | 0.838829 | 7374.04ms | 2090234 | 40 | 2.73834e+11 | 9.86371e+06 | 0.723826 | 12.2509 | 1(Tie) | true |
