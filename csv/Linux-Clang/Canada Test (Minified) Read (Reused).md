
----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 877.078 | 0.0700686 | 8671.41ms | 2090234 | 30 | 7.6082e+07 | 2.27278e+06 | 0.380806 | 2.82274 | 1(Win) | true |
| simdjson (ondemand) | 797.562 | 0.0583369 | 9392.83ms | 2090234 | 160 | 3.40148e+08 | 2.49937e+06 | 0.102822 | 3.10419 | 2(Loss) | true |
