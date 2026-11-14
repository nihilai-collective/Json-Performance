
----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10148.3 | 0.440844 | 546.853ms | 56369 | 320 | 174506 | 5297.19 | 0.313647 | 0.297173 | 1(Win) | true |
| simdjson (stage-1) | 9478.98 | 0.0951095 | 586.058ms | 56369 | 80 | 2327.53 | 5671.25 | 0.0220459 | 0.318122 | 2(Loss) | true |
