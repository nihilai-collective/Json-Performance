
----
### Twitter Partial Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 4341.89 | 1.08401 | 5018.82ms | 466906 | 80 | 9.88691e+07 | 102554 | 2.60743 | 1(Win) | true |
| Jsonifier STATISTICAL TIE | 4175.13 | 1.28461 | 5368.36ms | 466906 | 30 | 5.63094e+07 | 106650 | 0.809524 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 4087.56 | 0.349276 | 5819.66ms | 466906 | 40 | 5.79065e+06 | 108934 | 0.00979087 | 2(Tie) | true |
| simdjson (ondemand) | 3943.23 | 0.652487 | 5942ms | 466906 | 30 | 1.62861e+07 | 112922 | 0.0831947 | 4(Loss) | true |
| Glaze | 2579.12 | 0.216318 | 9167.59ms | 466906 | 160 | 2.23162e+07 | 172646 | 0.0666815 | 5(Loss) | true |
