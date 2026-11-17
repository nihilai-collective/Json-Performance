
----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 2370.55 | 0.326521 | 3428.1ms | 83958 | 160 | 1.94612e+06 | 33776.3 | 0.0817951 | 1.04351 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 2364.15 | 0.130522 | 3445.44ms | 83958 | 1280 | 2.50121e+06 | 33867.9 | 0.207917 | 1.04642 | 1(Tie) | true |
| Jsonifier | 2068.03 | 0.089474 | 3913.52ms | 83958 | 2560 | 3.07215e+06 | 38717.3 | 0.18242 | 1.19631 | 3(Loss) | true |
| simdjson (ondemand) | 2018.17 | 0.489478 | 4027.08ms | 83958 | 40 | 1.50847e+06 | 39673.8 | 0.0853109 | 1.2259 | 4(Loss) | true |
| Glaze | 1909.94 | 0.0654349 | 4212.98ms | 83958 | 4890 | 3.67971e+06 | 41922.1 | 0.0409533 | 1.29545 | 5(Loss) | true |
