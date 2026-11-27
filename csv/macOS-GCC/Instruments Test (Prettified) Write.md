
----
### Instruments Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 20556.2 | 0.12542 | 1006.07ms | 213963 | 2560 | 396798 | 9926.5 | 0.0754983 | 1(Win) | true |
| Glaze | 2424.4 | 0.15873 | 8583.08ms | 213963 | 320 | 5.71136e+06 | 84165.6 | 0.143321 | 2(Loss) | true |
| simdjson (reflection) | 355.492 | 0.203398 | 7504.61ms | 213963 | 40 | 5.45222e+07 | 573997 | 0.0464795 | 3(Loss) | true |
