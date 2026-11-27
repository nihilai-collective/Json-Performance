
----
### Discord Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12104.2 | 0.124709 | 461.247ms | 56369 | 80 | 2454.11 | 4441.25 | 0.084507 | 0.203159 | 1(Win) | true |
| Glaze | 3180.1 | 0.379547 | 1763.9ms | 56369 | 320 | 1.31728e+06 | 16904.4 | 0.272851 | 0.777227 | 2(Loss) | true |
