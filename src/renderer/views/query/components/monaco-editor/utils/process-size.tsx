export function processSize(size: number | string) {
  return !/^\d+$/.test(size.toString()) ? size : `${size}px`;
}
