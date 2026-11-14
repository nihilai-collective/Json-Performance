
----
### Canada Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 430.409 | 0.376161 | 7724.86ms | 2090234 | 80 | 2.42809e+10 | 4.63142e+06 | 0.0108486 | 7.06099 | 1(Win) | true |
| simdjson (ondemand) | 413.385 | 0.410373 | 8022.78ms | 2090234 | 80 | 3.13276e+10 | 4.82214e+06 | 0.0532464 | 7.35209 | 2(Loss) | true |
