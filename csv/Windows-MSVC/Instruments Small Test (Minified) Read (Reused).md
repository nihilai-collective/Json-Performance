
----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1045.36 | 0.127445 | 448.547ms | 4669 | 2560 | 75439.4 | 4259.49 | 0.143773 | 2.89289 | 1(Win) | true |
| simdjson (ondemand) | 928.614 | 0.166137 | 500.467ms | 4669 | 40 | 2538.46 | 4795 | 0.104384 | 3.25759 | 2(Loss) | true |
