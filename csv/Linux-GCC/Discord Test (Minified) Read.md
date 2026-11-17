
----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 20896.8 | 0.0761584 | 264.176ms | 56369 | 30 | 115.154 | 2572.53 | 0.0518027 | 0.117233 | 1(Win) | true |
| simdjson (stage-1) | 15870.1 | 0.0536031 | 343.274ms | 56369 | 40 | 131.874 | 3387.35 | 0.0113153 | 0.154747 | 2(Loss) | true |
