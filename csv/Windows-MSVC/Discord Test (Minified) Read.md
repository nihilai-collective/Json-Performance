
----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 10177.7 | 0.275959 | 529.955ms | 56369 | 2560 | 543889 | 5281.91 | 0.734851 | 0.296281 | 1(Win) | true |
| simdjson (stage-1) | 9314.74 | 0.433942 | 594.234ms | 56369 | 80 | 50175.6 | 5771.25 | 0.369565 | 0.3239 | 2(Loss) | true |
