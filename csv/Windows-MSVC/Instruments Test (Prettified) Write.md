
----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14157.9 | 0.0666043 | 1463.31ms | 213963 | 40 | 3685.9 | 14412.5 | 0.0404905 | 0.174509 | 1(Win) | true |
| Glaze | 3523.4 | 0.461009 | 5982.64ms | 213963 | 160 | 1.14049e+07 | 57913.1 | 0.508721 | 0.702304 | 2(Loss) | true |
