
----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2348.16 | 0.096291 | 3872.58ms | 83958 | 1280 | 1.37991e+06 | 34098.5 | 0.0111865 | 1.05352 | 1(Win) | true |
| simdjson (ondemand) | 2109.13 | 0.552141 | 4016.29ms | 83958 | 40 | 1.75743e+06 | 37962.8 | 0.104817 | 1.17292 | 2(Loss) | true |
