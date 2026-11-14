
----
### Discord Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 737.645 | 0.145029 | 5763.18ms | 83958 | 160 | 3.96514e+06 | 108546 | 0.405846 | 4.11936 | 1(Win) | true |
| simdjson (ondemand) | 266.062 | 0.124965 | 7825.5ms | 83958 | 320 | 4.52571e+07 | 300939 | 0.0856996 | 11.422 | 2(Loss) | true |
