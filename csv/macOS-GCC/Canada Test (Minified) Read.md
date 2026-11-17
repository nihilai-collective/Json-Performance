
----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7320.46 | 0.235993 | 7730.93ms | 2251027 | 640 | 3.06522e+08 | 293253 | 0.20201 | 1(Win) | true |
| simdjson (stage-1) | 5726.98 | 0.82849 | 9602.62ms | 2251027 | 40 | 3.85784e+08 | 374848 | 0.0763202 | 2(Loss) | true |
