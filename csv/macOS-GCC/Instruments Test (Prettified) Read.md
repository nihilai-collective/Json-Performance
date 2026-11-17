
----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2891.82 | 0.0469037 | 6243.64ms | 183677 | 4890 | 3.94719e+06 | 60573.5 | 1.59495 | 1(Win) | true |
| Jsonifier (two-stage) | 2201.52 | 0.142131 | 8050.05ms | 183677 | 4890 | 6.25387e+07 | 79566.8 | 0.202112 | 2(Loss) | true |
| Glaze | 1934.91 | 0.146202 | 9363.07ms | 183677 | 2560 | 4.48469e+07 | 90530.2 | 1.08454 | 3(Loss) | true |
| simdjson (reflection) | 1737.95 | 0.341184 | 5255.13ms | 183677 | 1280 | 1.51365e+08 | 100790 | 0.613926 | 4(Loss) | true |
| simdjson (ondemand) | 1535.69 | 1.26788 | 5699.5ms | 183677 | 30 | 6.27459e+07 | 114065 | 1.66985 | 5(Loss) | true |
