
----
### Canada Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7654.86 | 0.14698 | 6702.51ms | 2090234 | 40 | 5.8599e+06 | 260410 | 0.0307114 | 0.396981 | 1(Win) | true |
| simdjson (ondemand) | 6348.8 | 0.0985351 | 8016.85ms | 2090234 | 640 | 6.12588e+07 | 313981 | 0.0691204 | 0.478624 | 2(Loss) | true |
