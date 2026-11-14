
----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 246.197 | 0.247919 | 356.132ms | 905 | 4890 | 369367 | 3505.62 | 0.281157 | 12.2784 | 1(Win) | true |
| simdjson (ondemand) | 127.438 | 0.105573 | 692.499ms | 905 | 40 | 2044.87 | 6772.5 | 0.631501 | 23.786 | 2(Loss) | true |
