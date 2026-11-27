
----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1677.3 | 0.311618 | 8141.62ms | 264040 | 30 | 6.56573e+06 | 150127 | 0.045452 | 1(Win) | true |
| simdjson (ondemand) | 1255.69 | 0.312841 | 5108.98ms | 264040 | 30 | 1.1807e+07 | 200533 | 0.0467866 | 2(Loss) | true |
