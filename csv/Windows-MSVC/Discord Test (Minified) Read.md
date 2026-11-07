
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1306.83 | 0.216447 | 4163.65ms | 56369 | 640 | 5.0737e+06 | 41135.9 | 0.0144318 | 1.89259 | 1(Win) | true |
| Glaze | 1047.3 | 0.226652 | 5217.23ms | 56369 | 640 | 8.66248e+06 | 51330 | 0.0609177 | 2.36275 | 2(Loss) | true |
| Jsonifier (two-stage) | 1018.51 | 0.234734 | 5327.43ms | 56369 | 640 | 9.82396e+06 | 52780.9 | 0.189822 | 2.42951 | 3(Loss) | true |
| simdjson (ondemand) | 750.337 | 0.135146 | 7239.45ms | 56369 | 2560 | 2.40003e+07 | 71644.7 | 0.133868 | 3.29825 | 4(Loss) | true |
