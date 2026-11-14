
----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13998.2 | 1.0821 | 774.737ms | 108313 | 40 | 255044 | 7379.2 | 0.202781 | 1(Win) | true |
| simdjson (reflection) | 7760.24 | 0.182822 | 1339.06ms | 108313 | 4890 | 2.89586e+06 | 13310.8 | 0.392506 | 2(Loss) | true |
| Glaze | 1793.44 | 0.230785 | 5796.37ms | 108313 | 2560 | 4.52314e+07 | 57596.1 | 2.25564 | 3(Loss) | true |
