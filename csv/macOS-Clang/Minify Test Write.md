
----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 7413.11 | 0.205367 | 6328.65ms | 466906 | 640 | 9.73864e+06 | 60066.1 | 0.935284 | 1(Win) | true |
| Jsonifier | 7263.25 | 0.137658 | 6200.79ms | 466906 | 1280 | 9.11609e+06 | 61305.4 | 0.146626 | 2(Loss) | true |
| Glaze | 1730.32 | 0.103998 | 6771.8ms | 466906 | 1280 | 9.16777e+07 | 257337 | 0.0241786 | 3(Loss) | true |
